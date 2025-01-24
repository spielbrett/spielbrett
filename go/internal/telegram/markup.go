package telegram

import (
	"encoding/xml"
	"errors"

	"gopkg.in/telebot.v3"
)

type XMLBody struct {
	XMLName xml.Name `xml:"Body"`
	Label   XMLLabel `xml:"Label"`
	Grid    XMLGrid  `xml:"Grid"`
}

type XMLLabel struct {
	XMLName xml.Name `xml:"Label"`
	Content string   `xml:",chardata"`
}

type XMLButton struct {
	XMLName xml.Name `xml:"Button"`
	Action  string   `xml:"action,attr"`
	Content string   `xml:",chardata"`
}

type XMLGrid struct {
	XMLName xml.Name `xml:"Grid"`
	Rows    []XMLRow `xml:"Row"`
}

type XMLRow struct {
	XMLName xml.Name  `xml:"Row"`
	Cells   []XMLCell `xml:"Cell"`
}

type XMLCell struct {
	XMLName xml.Name  `xml:"Cell"`
	Button  XMLButton `xml:"Button"`
	Label   XMLLabel  `xml:"Label"`
}

const (
	ActionTag      = "action"
	NoOperationTag = "nop"
)

func (b *Bot) ConstructMarkup(instanceId string, markupStr string) (string, *telebot.ReplyMarkup, error) {
	var body XMLBody
	if err := xml.Unmarshal([]byte(markupStr), &body); err != nil {
		return "", nil, err
	}

	markup := b.NewMarkup()
	rows := make([]telebot.Row, 0, len(body.Grid.Rows))
	for _, xmlRow := range body.Grid.Rows {
		buttons := make([]telebot.Btn, 0, len(xmlRow.Cells))
		for _, xmlCell := range xmlRow.Cells {
			var btn telebot.Btn
			if (xmlCell.Button != XMLButton{}) {
				btn = markup.Data(xmlCell.Button.Content, ActionTag, instanceId, xmlCell.Button.Action)
			} else if (xmlCell.Label != XMLLabel{}) {
				btn = markup.Data(xmlCell.Label.Content, NoOperationTag)
			} else {
				return "", nil, errors.New("unsupported element")
			}
			buttons = append(buttons, btn)
		}
		rows = append(rows, buttons)
	}
	markup.Inline(rows...)

	return body.Label.Content, markup, nil
}
