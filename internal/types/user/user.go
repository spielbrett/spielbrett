package user

type User struct {
	Id          int64
	DisplayName string
	Auth        PasswordAuth
	Session     *Session
	Telegram    *Telegram
}
