<script lang="ts">
    import type Connection from "../lib/connection.svelte";

    export let connection: Connection;
</script>

<div class="connection-settings">
    <input name="instanceId" bind:value={connection.instanceId}/>
    <input name="userId" bind:value={connection.userId}/>
    <button name="connect" on:click={connection.connect}>Connect</button>
</div>
