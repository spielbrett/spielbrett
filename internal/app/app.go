package app

import (
	"github.com/spielbrett/spielbrett-api/gen/go/proto/services/instance_host"
	"github.com/spielbrett/spielbrett-go/internal/app/instance"
	"github.com/spielbrett/spielbrett-go/internal/app/user"
	"github.com/spielbrett/spielbrett-go/internal/storage"
)

type App struct {
	InstanceService *instance.Service
	UserService     *user.Service
}

func NewApp(
	storage storage.Storage,
	instanceHostClient instance_host.InstanceHostServiceClient,
	instanceHostEndpoint string,
) *App {
	return &App{
		InstanceService: instance.NewService(storage, instanceHostClient, instanceHostEndpoint),
		UserService:     user.NewService(storage),
	}
}
