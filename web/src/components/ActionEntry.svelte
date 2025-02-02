<script lang="ts">
    import type Connection from "../lib/connection.svelte";

    let { connection }: { connection: Connection } = $props();
</script>

<div class="action-entry">
    <input name="action" bind:value={connection.action}/>
    <button name="performAction" onclick={connection.performAction}>Perform</button>
</div>