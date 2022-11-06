package telegram

import (
	"fmt"

	telebot "gopkg.in/telebot.v3"
)

func (b *Bot) HandleCreate(c telebot.Context) error {
	chat := c.Chat()
	if chat.Type != telebot.ChatGroup && chat.Type != telebot.ChatSuperGroup {
		return c.Reply("Please add bot to a group chat before creating a game.")
	}

	instanceType := c.Data()
	if instanceType == "" {
		return c.Reply("Please provide a game type.")
	}

	instance, err := b.app.InstanceService.CreateInstance(instanceType)
	if err != nil {
		return c.Reply("Failed to create a game. Please try again.")
	}

	message := "Successfully created a game!"
	deepLinkedUrl := fmt.Sprintf("https://t.me/%s?start=%s", c.Bot().Me.Username, instance.Uid)

	markup := c.Bot().NewMarkup()
	markup.Inline(
		markup.Row(
			markup.URL("Join game", deepLinkedUrl),
		),
	)

	return c.Reply(message, markup)
}
