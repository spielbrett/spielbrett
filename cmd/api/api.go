package main

import (
	"context"
	"log"
	"net"
	"os"
	"time"

	instanceProto "github.com/spielbrett/spielbrett/gen/go/proto/services/instance"
	instanceHostProto "github.com/spielbrett/spielbrett/gen/go/proto/services/instance_host"
	userProto "github.com/spielbrett/spielbrett/gen/go/proto/services/user"
	"github.com/spielbrett/spielbrett/internal/app"
	"github.com/spielbrett/spielbrett/internal/grpc/instance"
	"github.com/spielbrett/spielbrett/internal/grpc/user"
	"github.com/spielbrett/spielbrett/internal/storage/mongo"
	"github.com/spielbrett/spielbrett/internal/telegram"
	mongodriver "go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
	"google.golang.org/grpc/reflection"
)

var MONGO_TIMEOUT = 10 * time.Second

func main() {
	botToken, ok := os.LookupEnv("TELEGRAM_BOT_TOKEN")
	if !ok {
		log.Fatal("TELEGRAM_BOT_TOKEN not set")
	}
	listenAddr, ok := os.LookupEnv("GRPC_LISTEN_ADDR")
	if !ok {
		log.Fatal("GRPC_LISTEN_ADDR not set")
	}
	mongoEndpoint, ok := os.LookupEnv("MONGO_ENDPOINT")
	if !ok {
		log.Fatal("MONGO_ENDPOINT not set")
	}
	instanceHostEndpoint, ok := os.LookupEnv("INSTANCE_HOST_ENDPOINT")
	if !ok {
		log.Fatal("INSTANCE_HOST_ENDPOINT not set")
	}

	ctx, cancel := context.WithTimeout(context.Background(), MONGO_TIMEOUT)
	defer cancel()
	mongoClient, err := mongodriver.Connect(ctx, options.Client().ApplyURI(mongoEndpoint))
	if err != nil {
		log.Fatal(err)
	}
	storage := mongo.NewStorage(mongoClient)

	conn, err := grpc.Dial(instanceHostEndpoint, grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		log.Fatal(err)
	}
	defer conn.Close()
	instanceHostClient := instanceHostProto.NewInstanceHostServiceClient(conn)

	app := app.NewApp(storage, instanceHostClient, instanceHostEndpoint)

	bot, err := telegram.NewBot(app, botToken)
	if err != nil {
		log.Fatal(err)
	}
	go bot.Start()

	lis, err := net.Listen("tcp", listenAddr)
	if err != nil {
		log.Fatalf("failed to listen: %v", err)
	}

	var opts []grpc.ServerOption
	grpcServer := grpc.NewServer(opts...)

	instanceProto.RegisterInstanceServiceServer(grpcServer, instance.NewGRPCService(app.InstanceService))
	userProto.RegisterUserServiceServer(grpcServer, user.NewGRPCService(app.UserService))
	reflection.Register(grpcServer)

	grpcServer.Serve(lis)
}
