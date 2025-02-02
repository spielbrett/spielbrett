<script lang="ts">
    import type Connection from "../lib/connection.svelte";

    let { connection }: { connection: Connection } = $props();
</script>

<div class="connection-settings">
    <input name="instanceId" bind:value={connection.instanceId}/>
    <input name="userId" bind:value={connection.userId}/>
    <button name="connect" onclick={connection.connect}>Connect</button>
</div>
