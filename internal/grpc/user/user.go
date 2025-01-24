package user

import (
	"context"
	"errors"

	proto "github.com/spielbrett/spielbrett/gen/go/proto/services/user"
	"github.com/spielbrett/spielbrett/internal/app/user"
)

type GRPCService struct {
	proto.UserServiceServer
	appService *user.Service
}

func NewGRPCService(appService *user.Service) *GRPCService {
	return &GRPCService{
		appService: appService,
	}
}

func (s *GRPCService) RegisterUser(c context.Context, r *proto.RegisterUserRequest) (*proto.RegisterUserResponse, error) {
	return nil, errors.New("not implemented")
}

func (s *GRPCService) LinkTelegram(c context.Context, r *proto.LinkTelegramRequest) (*proto.LinkTelegramResponse, error) {
	return nil, errors.New("not implemented")
}

func (s *GRPCService) LoginPassAuth(c context.Context, r *proto.LoginPassAuthRequest) (*proto.LoginPassAuthResponse, error) {
	return nil, errors.New("not implemented")
}

func (s *GRPCService) TelegramAuth(c context.Context, r *proto.TelegramAuthRequest) (*proto.TelegramAuthResponse, error) {
	return nil, errors.New("not implemented")
}
