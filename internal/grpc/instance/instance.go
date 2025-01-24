package instance

import (
	"context"

	proto "github.com/spielbrett/spielbrett/gen/go/proto/services/instance"
	"github.com/spielbrett/spielbrett/internal/app/instance"
)

type GRPCService struct {
	proto.InstanceServiceServer
	appService *instance.Service
}

func NewGRPCService(appService *instance.Service) *GRPCService {
	return &GRPCService{
		appService: appService,
	}
}

func (s *GRPCService) CreateInstance(c context.Context, r *proto.CreateInstanceRequest) (*proto.CreateInstanceResponse, error) {
	return nil, nil
}
