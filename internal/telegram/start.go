package telegram

import (
	"fmt"

	telebot "gopkg.in/telebot.v3"
)

func (b *Bot) HandleStart(c telebot.Context) error {
	if c.Data() != "" {
		return b.HandleDeepLinkedStart(c)
	} else {
		return b.HandleNormalStart(c)
	}
}

func (b *Bot) HandleDeepLinkedStart(c telebot.Context) error {
	instanceId := c.Data()

	message := "You have been invited to play a game!"
	webAppUrl := fmt.Sprintf("https://localhost/%s", instanceId)

	markup := b.NewMarkup()
	markup.Inline(
		markup.Row(
			markup.WebApp("Join", &telebot.WebApp{
				URL: webAppUrl,
			}),
		),
	)

	return c.Reply(message, markup)
}

func (b *Bot) HandleNormalStart(c telebot.Context) error {
	return c.Reply("Welcome!")
}
