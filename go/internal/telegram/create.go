package telegram

import (
	"fmt"
	"strconv"
	"strings"

	telebot "gopkg.in/telebot.v3"
)

func (b *Bot) HandleCreate(c telebot.Context) error {
	chat := c.Chat()
	if chat.Type != telebot.ChatGroup && chat.Type != telebot.ChatSuperGroup {
		return c.Reply("Please add bot to a group chat before creating a game.")
	}

	data := c.Data()
	if data == "" {
		return c.Reply("Please provide a game type and invited players list.")
	}

	tokens := strings.Split(data, " ")
	instanceType := tokens[0]

	userIds := make([]string, 0, len(tokens))
	userIds = append(userIds, strconv.FormatInt(c.Sender().ID, 10))
	for _, token := range tokens[1:] {
		if !strings.HasPrefix(token, "@") {
			return c.Reply("Invited players must be specified by their usernames.")
		}
		username := strings.TrimPrefix(token, "@")
		userId, ok := b.usernameCache[username]
		if !ok {
			return c.Reply(fmt.Sprintf(
				"Failed to retrieve the user ID for @%s.\n"+
					"The user appears to have never interacted with the bot.",
				username,
			))
		}
		userIds = append(userIds, strconv.FormatInt(userId, 10))
	}

	instance, gameMarkup, err := b.app.InstanceService.CreateInstance(instanceType, userIds)
	if err != nil {
		return c.Reply("Failed to create a game. Please try again.")
	}
	b.markup[instance.Uid] = gameMarkup

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
