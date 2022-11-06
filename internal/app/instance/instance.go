package instance

import (
	"github.com/spielbrett/spielbrett-go/internal/storage"
	"github.com/spielbrett/spielbrett-go/internal/types/instance"
)

type Service struct {
	storage storage.Storage
}

func NewService(storage storage.Storage) *Service {
	return &Service{
		storage: storage,
	}
}

func (s *Service) CreateInstance(instanceType string) (instance.Instance, error) {
	return instance.Instance{
		Uid:      "test",
		Type:     instanceType,
		Endpoint: "",
	}, nil
}
