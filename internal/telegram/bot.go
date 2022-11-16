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

	// TODO: Better types
	usernameCache map[string]int64
	markup        map[string]map[string]string
	widgets       map[string]map[int64]telebot.Editable
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

		usernameCache: make(map[string]int64),
		markup:        make(map[string]map[string]string),
		widgets:       make(map[string]map[int64]telebot.Editable),
	}

	b.Use(middleware.Logger())
	b.Use(bot.usernameCacheMiddleware)

	b.Handle("/start", bot.HandleStart)
	b.Handle("/create", bot.HandleCreate)
	b.Handle(telebot.OnCallback, bot.HandleCallback)

	return bot, nil
}

func (b *Bot) usernameCacheMiddleware(next telebot.HandlerFunc) telebot.HandlerFunc {
	return func(c telebot.Context) error {
		if sender := c.Sender(); sender != nil {
			if sender.Username != "" {
				b.usernameCache[sender.Username] = sender.ID
			}
		}
		return next(c)
	}
}
