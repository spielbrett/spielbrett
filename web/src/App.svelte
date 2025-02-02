<script lang="ts">
    import Board from './components/Board.svelte'
    import ConnectionSettings from './components/ConnectionSettings.svelte';
    import ConnectionStatus from './components/ConnectionStatus.svelte';
    import type Connection from './lib/connection.svelte';

    export let connection: Connection;
</script>

<main>
    <ConnectionSettings connection={connection}/>
    <ConnectionStatus connected={connection.connected}/>
    <Board lastMessage={connection.lastMessage}/>
</main>
