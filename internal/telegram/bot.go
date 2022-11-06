package telegram

import (
	"time"

	"github.com/spielbrett/spielbrett-go/internal/app"
	telebot "gopkg.in/telebot.v3"
	"gopkg.in/telebot.v3/middleware"
)

const LONG_POLLER_TIMEOUT = 10 * time.Second

type Bot struct {
	*telebot.Bot
	app *app.App
}

func NewBot(app *app.App, token string) (*Bot, error) {
	pref := telebot.Settings{
		Token:  token,
		Poller: &telebot.LongPoller{Timeout: LONG_POLLER_TIMEOUT},
	}

	b, err := telebot.NewBot(pref)
	if err != nil {
		return nil, err
	}

	bot := &Bot{
		Bot: b,
		app: app,
	}

	b.Use(middleware.Logger())

	b.Handle("/start", bot.HandleStart)
	b.Handle("/create", bot.HandleCreate)

	return bot, nil
}
