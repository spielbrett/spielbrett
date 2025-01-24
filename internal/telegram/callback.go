package telegram

import (
	"errors"
	"strconv"
	"strings"

	telebot "gopkg.in/telebot.v3"
)

func (b *Bot) HandleCallback(c telebot.Context) error {
	// TODO: Handle this more idiomatically
	tokens := strings.Split(c.Callback().Data, "|")
	unique := strings.TrimPrefix(tokens[0], "\u000c")

	if unique == NoOperationTag {
		return c.Respond()
	} else if unique == ActionTag {
		return b.HandleAction(c)
	}

	return errors.New("unsupported callback")
}

func (b *Bot) HandleAction(c telebot.Context) error {
	tokens := strings.Split(c.Callback().Data, "|")
	if len(tokens) != 3 {
		return errors.New("malformed callback data")
	}

	instanceId := tokens[1]
	userId := strconv.FormatInt(c.Sender().ID, 10)
	action := tokens[2]

	markup, err := b.app.InstanceManager.PerformAction(instanceId, userId, action)
	if err != nil {
		return err
	}
	b.markup[instanceId] = markup

	widgets, ok := b.widgets[instanceId]
	if !ok {
		return nil
	}

	for widgetUserId, widget := range widgets {
		widgetUserIdStr := strconv.FormatInt(widgetUserId, 10)
		userMarkupStr := markup[widgetUserIdStr]

		message, userMarkup, err := b.ConstructMarkup(instanceId, userMarkupStr)
		if err != nil {
			return err
		}
		b.Edit(widget, message, userMarkup)
	}

	return c.Respond(&telebot.CallbackResponse{
		Text:      "OK!",
		ShowAlert: false,
	})
}
