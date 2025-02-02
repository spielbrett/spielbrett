<script lang="ts">
    let { connected }: { connected: boolean } = $props();
</script>

<div class="connection-status">
    {connected ? "connected" : "disconnected"}
</div>