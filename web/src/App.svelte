<script lang="ts">
    import ActionEntry from './components/ActionEntry.svelte';
    import Board from './components/Board.svelte'
    import ConnectionSettings from './components/ConnectionSettings.svelte';
    import ConnectionStatus from './components/ConnectionStatus.svelte';
    import type Connection from './lib/connection.svelte';

    let { connection }: { connection: Connection } = $props();
</script>

<main>
    <ConnectionSettings connection={connection}/>
    <ConnectionStatus connected={connection.connected}/>
    <Board lastMessage={connection.lastMessage}/>
    <ActionEntry connection={connection}/>
</main>
