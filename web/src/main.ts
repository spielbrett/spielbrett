import App from './App.svelte'
import Connection from './lib/connection.svelte';

import { mount } from 'svelte'

let connection = new Connection('ws://127.0.0.1:8080');

const app = mount(App, {
    target: document.getElementById('app')!,
    props: { connection: connection }
})

export default app;
