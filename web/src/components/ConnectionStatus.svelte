<script lang="ts">
    export let connected: boolean;
</script>

<div class="connection-status">
    {connected ? "connected" : "disconnected"}
</div>