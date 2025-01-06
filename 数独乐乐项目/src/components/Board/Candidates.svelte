<script>
	import { CANDIDATE_COORDS ,BOX_SIZE, GRID_LENGTH, SUDOKU_SIZE, GRID_COORDS} from '@sudoku/constants';
	import { cursor } from '@sudoku/stores/cursor';
	import { userGrid } from '@sudoku/stores/grid';
	import { notes } from '@sudoku/stores/notes';
	import { candidates } from '@sudoku/stores/candidates';
	import {num} from '@sudoku/stores/currentValueStore';
    import { tick } from 'svelte';  // 导入 tick() 来手动触发视图更新
	export let candidates1 = [];
	export let cellX;
	export let cellY;


	let pos={x:cellX-1,y:cellY-1}; // 需要传入当前格子的位置
	// 订阅禁用候选值的状态
	
	// 订阅禁用候选值的状态
	let value = new Set();
	let cellXY;
	userGrid.disabledCandidates.subscribe(($disabledCandidates) => {
	    // 假设 $disabledCandidates 是一个 Map
	    // 检查当前格子是否有禁用的候选项

		cellXY=`${pos.y},${pos.x}`;
		if ($disabledCandidates && $disabledCandidates.has(cellXY)) {
		    //console.log($disabledCandidates.get(cellXY)); // 获取禁用的候选项
			value=$disabledCandidates.get(cellXY);
		}

	
	});

     function handleCandidateClick(index) {
	    const candidate = index + 1;  // 候选数字的值
         // console.log("wode11111"+$cursor);
         cursor.set(cellX - 1, cellY - 1);
	    userGrid.set($cursor, candidate,true);
         // console.log("wode22222"+$cursor);
		for (let cell = 0; cell < GRID_LENGTH; cell++) {
			const [row, col] = GRID_COORDS[cell];
			let pos={x:row,y:col};
		if ($candidates.hasOwnProperty(pos.x + ',' + pos.y)) {
			candidates.clear(pos);
		}
		}
		userGrid.applyHint($cursor);
		num.set(1);


    }

	  
	
</script>

<div class="candidate-grid">
    <!-- 当 candidates1 的长度大于 1 时，显示候选项 -->
    {#each CANDIDATE_COORDS as [row, col], index}
      <div class="candidate row-start-{row} col-start-{col}"
           class:invisible={!candidates1.includes(index + 1)}
           class:visible={candidates1.includes(index + 1)}
           class:disabled={value.has(index + 1)} 
           class:active={!value.has(index + 1)}
           on:click={(event) => {
             // 只有当当前候选项可见且未禁用时才触发点击事件
              // 阻止事件冒泡，防止父组件的点击事件被触发
               event.stopPropagation();
             if (candidates1.includes(index + 1) && !value.has(index + 1)) {
               handleCandidateClick(index);
             }
           }}>
        {index + 1}
      </div>
    {/each}

  
</div>

<style>
	.candidate-grid {
	    @apply grid grid-cols-3 grid-rows-3 gap-2 p-1; /* 3x3 grid，调整间隔 */
	    width: 100%; /* 100% 宽度 */
	    height: 100%; /* 100% 高度 */
		background: rgba(35,255,35,0.6); /* 去掉背景 */
	}
	
	.candidate {
	    @apply flex items-center justify-center text-center bg-gray-200 rounded-lg text-white;
	    width: 100%; /* 填满格子宽度 */
	    height: 100%; /* 填满格子高度 */
	    font-size: 1.1rem; /* 设置合适的字体大小 */
	    line-height: 0.4; /* 设置合适的行高，确保文本不溢出 */
		background: none; /* 去掉背景 */
		
	}
	.candidate.disabled {
	    background-color: #d3d3d3; /* 灰色背景 */
	    color: #a9a9a9; /* 灰色字体 */
	    cursor: not-allowed; /* 禁用光标 */
	  }
	

</style>