class Connection {
    public connected: boolean = $state(false);
    public lastMessage: string = $state("");

    private socket: WebSocket;

    constructor(url: string) {
        this.socket = new WebSocket(url);

        this.socket.onopen = this.onOpen.bind(this);
        this.socket.onclose = this.onClose.bind(this);
        this.socket.onerror = this.onError.bind(this);
        this.socket.onmessage = this.onMessage.bind(this);
    }

    private onOpen(): void {
        this.connected = true;
        this.socket.send("12345");
    }

    private onClose(event: CloseEvent): void {
        this.connected = false;
    }

    private onError(error: Event): void {
        this.connected = false;
    }

    private onMessage(event: MessageEvent): void {
        this.lastMessage = event.data;
    }
}

export default Connection;