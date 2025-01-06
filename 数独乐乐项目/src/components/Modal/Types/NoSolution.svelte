<script>
    export let data ;
    export let hideModal;
    import { invalidCells } from '@sudoku/stores/grid';
    import { cursor } from "@sudoku/stores/cursor";
    function handleContinue() {
        //console.log("data.callback:", data, typeof data.callback); // 调试输出
        // console.log("wudi",data.callback1);
        if(data.callback)data.callback();
        // invalidCells.subscribe(($invalidCells) => {
        //     // 找到元素的索引
        //    // console.log("changdu",$invalidCells.length,$invalidCells[0],$invalidCells[1]) ;
        //     let index = $invalidCells.indexOf($cursor.x + ',' +$cursor.y);
        //     console.log(index);
        //     if (index !== -1) {
        //         $invalidCells.splice(index, 1);  // 从索引位置删除 1 个元素
        //     }
        //     // console.log("changdu",$invalidCells.length,$invalidCells[0],$invalidCells[1]) ;
        // });

        hideModal();

    }
</script>

<h1 class="text-3xl font-semibold mb-5 leading-none">No Solution</h1>

<p class="text-lg mb-5">No Solution in current try, Go back find other way.</p>

<div class="flex justify-end">
    <button class="btn btn-small mr-3" on:click={hideModal}>Cancel</button>
    <button class="btn btn-small btn-primary" on:click={handleContinue}
        >Continue</button
    >
</div>
