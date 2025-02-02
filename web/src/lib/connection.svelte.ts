class Connection {
    public instanceId: string = $state("");
    public userId: string = $state("");
    public connected: boolean = $state(false);
    public lastMessage: string = $state("");
    public action: string = $state("");

    private url: string;
    private socket: WebSocket | null;

    constructor(url: string) {
        this.url = url;
        this.socket = null;
    }

    public connect = (): void => {
        this.socket = new WebSocket(this.url);

        this.socket.onopen = this.onOpen;
        this.socket.onclose = this.onClose;
        this.socket.onerror = this.onError;
        this.socket.onmessage = this.onMessage;
    }

    public performAction = (): void => {
        this.socket?.send(JSON.stringify({
            message: "performAction",
            payload: JSON.parse(this.action)
        }));
    }

    private onOpen = (): void => {
        this.connected = true;
        this.socket!.send(JSON.stringify({
            message: "render",
            payload: {
                instanceId: this.instanceId,
                userId: this.userId
            }
        }));
    }

    private onClose = (event: CloseEvent): void => {
        this.connected = false;
    }

    private onError = (error: Event): void => {
        this.connected = false;
    }

    private onMessage = (event: MessageEvent): void => {
        this.lastMessage = event.data;
    }
}

export default Connection;