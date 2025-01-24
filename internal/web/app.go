package web

import (
	"net/http"

	"github.com/spielbrett/spielbrett/internal/app"
)

type App struct {
	*http.Server
	app *app.App
}

func NewApp(app *app.App, httpListenAddr string) *App {
	server := &http.Server{
		Addr: httpListenAddr,
	}

	webApp := &App{
		Server: server,
		app:    app,
	}

	return webApp
}
