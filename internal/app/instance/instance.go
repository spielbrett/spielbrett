package instance

import (
	"context"

	"github.com/spielbrett/spielbrett/gen/go/proto/services/instance_host"
	"github.com/spielbrett/spielbrett/internal/storage"
	"github.com/spielbrett/spielbrett/internal/types/instance"
)

type Service struct {
	storage              storage.Storage
	instanceHostClient   instance_host.InstanceHostServiceClient
	instanceHostEndpoint string
}

func NewService(
	storage storage.Storage,
	instanceHostClient instance_host.InstanceHostServiceClient,
	instanceHostEndpoint string,
) *Service {
	return &Service{
		storage:              storage,
		instanceHostClient:   instanceHostClient,
		instanceHostEndpoint: instanceHostEndpoint,
	}
}

func (s *Service) CreateInstance(instanceType string, userIds []string) (instance.Instance, map[string]string, error) {
	response, err := s.instanceHostClient.CreateInstance(
		context.Background(),
		&instance_host.CreateInstanceRequest{
			InstanceType: instanceType,
			UserIds:      userIds,
		},
	)
	if err != nil {
		return instance.Instance{}, nil, err
	}

	return instance.Instance{
		Uid:      response.InstanceId,
		Type:     instanceType,
		Endpoint: s.instanceHostEndpoint,
	}, response.Markup, nil
}

func (s *Service) PerformAction(instanceId string, userId string, action string) (map[string]string, error) {
	response, err := s.instanceHostClient.PerformAction(
		context.Background(),
		&instance_host.PerformActionRequest{
			InstanceId: instanceId,
			UserId:     userId,
			Action:     action,
		},
	)
	if err != nil {
		return nil, err
	}

	return response.Markup, nil
}
