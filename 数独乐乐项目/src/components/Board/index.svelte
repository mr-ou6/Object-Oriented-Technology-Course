<script>
	import { BOX_SIZE } from '@sudoku/constants';
	import { gamePaused } from '@sudoku/stores/game';
	import { grid, userGrid, invalidCells } from '@sudoku/stores/grid';
	import { settings } from '@sudoku/stores/settings';
	import { cursor } from '@sudoku/stores/cursor';
	import { candidates } from '@sudoku/stores/candidates';
	import { currentValueStore } from '@sudoku/stores/currentValueStore';
	import Cell from './Cell.svelte';

	function isSelected(cursorStore, x, y) {
		return cursorStore.x === x && cursorStore.y === y;
	}

	function isSameArea(cursorStore, x, y) {
		if (cursorStore.x === null && cursorStore.y === null) return false;
		if (cursorStore.x === x || cursorStore.y === y) return true;

		const cursorBoxX = Math.floor(cursorStore.x / BOX_SIZE);
		const cursorBoxY = Math.floor(cursorStore.y / BOX_SIZE);
		const cellBoxX = Math.floor(x / BOX_SIZE);
		const cellBoxY = Math.floor(y / BOX_SIZE);
		return (cursorBoxX === cellBoxX && cursorBoxY === cellBoxY);
	}

	function getValueAtCursor(gridStore, cursorStore) {
		if (cursorStore.x === null && cursorStore.y === null) return null;

		return gridStore[cursorStore.y][cursorStore.x];
	}

	
</script>

<div class="all">
	<div class="board-padding relative z-10">
		<div class="max-w-xl relative">
			<div class="w-full" style="padding-top: 100%"></div>
		</div>
		<div class="board-padding absolute inset-0 flex justify-center">

			<div class="bg-white shadow-2xl rounded-xl overflow-hidden w-full h-full max-w-xl grid" class:bg-gray-200={$gamePaused}>

				{#each $userGrid as row, y}
					{#each row as value, x}
						<Cell {value}
							cellY={y + 1}
							cellX={x + 1}
							candidates1={$candidates[x + ',' + y]}
							hintsLevel={$settings.hintsLevel}
							disabled={$gamePaused}
							selected={isSelected($cursor, x, y)}
							userNumber={$grid[y][x] === 0}
							sameArea={$settings.highlightCells && !isSelected($cursor, x, y) && isSameArea($cursor, x, y)}
							sameNumber={$settings.highlightSame && value && !isSelected($cursor, x, y) && getValueAtCursor($userGrid, $cursor) === value}
							conflictingNumber={$settings.highlightConflicting && $grid[y][x] === 0 && $invalidCells.includes(x + ',' + y)} />
					{/each}
				{/each}

			</div>

		</div>
		
	</div>
	<div class="px-4 pb-5 flex justify-center">
		<div class="w-full max-w-xl">
			<div class="container">
				<!-- 显示收到的值，放到右边 -->
				<p class="right-side">{$currentValueStore}</p>
			</div>
		</div>
	</div>
</div>
<style>
	.board-padding {
		@apply px-4 pb-4;
	}
  .container {
    display: flex;          /* 使用 flex 布局 */
    justify-content: flex-end;  /* 将内容对齐到右侧 */
    width: 100%;            /* 让容器占满可用空间 */
    padding: 10px;          /* 添加适当的内边距 */
    box-sizing: border-box; /* 确保边框和内边距不影响容器尺寸 */
  }
  
  .right-side {
    white-space: nowrap;    /* 防止文本换行 */
    font-size: 16px;         /* 调整字体大小，视情况而定 */
  }
</style>