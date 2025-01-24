package telegram

import (
	"strconv"

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

	markups, ok := b.markup[instanceId]
	if !ok {
		return c.Reply("You have joined the game that does not currently exist.")
	}

	userId := c.Sender().ID
	userIdStr := strconv.FormatInt(userId, 10)
	markup, ok := markups[userIdStr]
	if !ok {
		return c.Reply("You have joined the game you've not been invited to.")
	}

	message, replyMarkup, err := b.ConstructMarkup(instanceId, markup)
	if err != nil {
		// TODO: Handle invalid markup
		return err
	}

	widget, err := b.Send(c.Sender(), message, replyMarkup)
	if err != nil {
		return err
	}

	if _, ok := b.widgets[instanceId]; !ok {
		b.widgets[instanceId] = make(map[int64]telebot.Editable)
	}
	b.widgets[instanceId][userId] = widget
	return nil
}

func (b *Bot) HandleNormalStart(c telebot.Context) error {
	return c.Reply("Welcome!")
}
