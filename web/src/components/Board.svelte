<script lang="ts">
    let { lastMessage }: { lastMessage: string } = $props();
</script>

<div class="board">
    {lastMessage}
</div>