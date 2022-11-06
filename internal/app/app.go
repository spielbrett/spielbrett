package app

import (
	"github.com/spielbrett/spielbrett-go/internal/app/instance"
	"github.com/spielbrett/spielbrett-go/internal/app/user"
	"github.com/spielbrett/spielbrett-go/internal/storage"
)

type App struct {
	InstanceService *instance.Service
	UserService     *user.Service
}

func NewApp(storage storage.Storage) *App {
	return &App{
		InstanceService: instance.NewService(storage),
		UserService:     user.NewService(storage),
	}
}
