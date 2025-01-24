package app

import (
	"github.com/spielbrett/spielbrett/gen/go/proto/instance_host"
	"github.com/spielbrett/spielbrett/internal/app/instance"
)

type App struct {
	InstanceManager *instance.Service
}

func NewApp(
	instanceHostClient instance_host.InstanceHostServiceClient,
	instanceHostEndpoint string,
) *App {
	return &App{
		InstanceManager: instance.NewService(instanceHostClient, instanceHostEndpoint),
	}
}
