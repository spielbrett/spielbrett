package mongo

import "go.mongodb.org/mongo-driver/mongo"

type Storage struct {
	client *mongo.Client
}

func NewStorage(client *mongo.Client) *Storage {
	return &Storage{
		client: client,
	}
}
