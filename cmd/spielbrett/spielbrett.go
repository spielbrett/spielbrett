package main

import (
	"log"
	"os"
	"time"

	instanceHostProto "github.com/spielbrett/spielbrett/gen/go/proto/instance_host"
	"github.com/spielbrett/spielbrett/internal/app"
	"github.com/spielbrett/spielbrett/internal/telegram"
	"github.com/spielbrett/spielbrett/internal/web"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
)

var MONGO_TIMEOUT = 10 * time.Second

func main() {
	botToken, ok := os.LookupEnv("TELEGRAM_BOT_TOKEN")
	if !ok {
		log.Fatal("TELEGRAM_BOT_TOKEN not set")
	}
	instanceHostEndpoint, ok := os.LookupEnv("INSTANCE_HOST_ENDPOINT")
	if !ok {
		log.Fatal("INSTANCE_HOST_ENDPOINT not set")
	}
	httpListenAddr, ok := os.LookupEnv("HTTP_LISTEN_ADDR")
	if !ok {
		log.Fatal("HTTP_LISTEN_ADDR not set")
	}

	conn, err := grpc.NewClient(instanceHostEndpoint, grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		log.Fatal(err)
	}
	defer conn.Close()
	instanceHostClient := instanceHostProto.NewInstanceHostServiceClient(conn)

	app := app.NewApp(instanceHostClient, instanceHostEndpoint)

	bot, err := telegram.NewBot(app, botToken)
	if err != nil {
		log.Fatal(err)
	}
	go bot.Start()

	webApp := web.NewApp(app, httpListenAddr)
	if err := webApp.ListenAndServe(); err != nil {
		log.Fatal(err)
	}
}
