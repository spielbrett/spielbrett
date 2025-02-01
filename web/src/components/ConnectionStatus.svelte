<script lang="ts">
    export let connected: boolean;
</script>

<div class="status">
    {connected ? "connected" : "disconnected"}
</div>