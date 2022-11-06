package user

import "github.com/spielbrett/spielbrett-go/internal/storage"

type Service struct {
	storage storage.Storage
}

func NewService(storage storage.Storage) *Service {
	return &Service{
		storage: storage,
	}
}
