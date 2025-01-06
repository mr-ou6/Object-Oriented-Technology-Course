<script>
	import { candidates } from '@sudoku/stores/candidates';
	import { userGrid } from '@sudoku/stores/grid';
	import { cursor } from '@sudoku/stores/cursor';
	import { CANDIDATE_COORDS ,BOX_SIZE, GRID_LENGTH, SUDOKU_SIZE, GRID_COORDS} from '@sudoku/constants';
	import { notes } from '@sudoku/stores/notes';
	import { settings } from '@sudoku/stores/settings';
	import { keyboardDisabled } from '@sudoku/stores/keyboard';
	import { gamePaused } from '@sudoku/stores/game';
	import {num} from '@sudoku/stores/currentValueStore';
	import { modal } from '@sudoku/stores/modal';
	
	let lastClickTime = 0;
	let timeoutId = null;
	
	function handleClick(event) {
	  const currentTime = Date.now();
	  const timeDiff = currentTime - lastClickTime;
	
	  if (timeDiff < 300) {  // 判断是否为双击
	    clearTimeout(timeoutId); // 清除单击的延时
	    handleDoubleClick(event);
	  } else {  // 如果是单击
	    timeoutId = setTimeout(() => {
	     handleHint(event);
	    }, 300);  // 延时300ms处理单击事件
	  }
	
	  lastClickTime = currentTime; // 更新最后点击时间
	}
	
	function handleHint() {
		let num1=$num;
		if(num1<$settings.hintsLevel){
			//清空candidateOnlySet
			userGrid.candidateonlySet.set(new Set());
			userGrid.applyHint($cursor);
			num.set(num1+1);
		}
		else if(num1===$settings.hintsLevel){
			num.set(1);
		}

	}
	function handleDoubleClick() {
		//清空candidateOnlySet
		userGrid.candidateonlySet.set(new Set());
		for (let cell = 0; cell < GRID_LENGTH; cell++) {
			const [row, col] = GRID_COORDS[cell];
			let pos={x:row,y:col};
			if ($candidates.hasOwnProperty(pos.x + ',' + pos.y)) {
				candidates.clear(pos);
			}
		}
		//显示等级清除
		num.set(0);	
	}
	
	let isUndoable;
	let isRedoable;
	let isBackToBranchable;
	userGrid.isUndoable.subscribe(value => {
		isUndoable = value;
	});
	userGrid.isRedoable.subscribe(value => {
		isRedoable = value;
	});
	userGrid.isBackToBranchable.subscribe(value => {
			isBackToBranchable = value;
		});
	function handleUndo() {
		
		userGrid.undo();
		console.log('Undo button clicked');
	}
	function handleRedo() {
		console.log('Redo button clicked');
		userGrid.redo();
	}
	function handleBackToBranch() {
			console.log('BackToBranch button clicked');
			userGrid.backToBranch();
		}
	
	function openSettings() {
		modal.show('settings');
	}
	
	function hideModal() {
		modal.hide();
	}
</script>

<div class="action-buttons space-x-3">

	<button class="btn btn-round btn-badge" disabled={$gamePaused || !isBackToBranchable} title="BackToBranch" on:click={handleBackToBranch}>
		<svg class="icon-outline" xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor">
			<path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M4 4v5h.582M4 4h5M4 4l1.5 1.5M20 20v-5h-.582M20 20h-5M20 20l-1.5-1.5M4 12a8 8 0 0116 0M4 12a8 8 0 0016 0" />
		</svg>
		
		{#if isBackToBranchable}
			<span class="badge" class:badge-primary={isBackToBranchable}>{isBackToBranchable}</span>
		{/if}
	</button>

	<button class="btn btn-round" disabled={$gamePaused || !isUndoable} title="Undo" on:click={handleUndo}>
		<svg class="icon-outline" xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor">
			<path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M3 10h10a8 8 0 018 8v2M3 10l6 6m-6-6l6-6" />
		</svg>
	</button>

	<button class="btn btn-round" disabled={$gamePaused || !isRedoable} title="Redo" on:click={handleRedo}>
		<svg class="icon-outline" xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor">
			<path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M21 10h-10a8 8 90 00-8 8v2M21 10l-6 6m6-6l-6-6" />
		</svg>
	</button>

	<button class="btn btn-round btn-badge"  on:click={handleClick} title="Hint">
		<svg class="icon-outline" xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor">
			<path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M9.663 17h4.673M12 3v1m6.364 1.636l-.707.707M21 12h-1M4 12H3m3.343-5.657l-.707-.707m2.828 9.9a5 5 0 117.072 0l-.548.547A3.374 3.374 0 0014 18.469V19a2 2 0 11-4 0v-.531c0-.895-.356-1.754-.988-2.386l-.548-.547z" />
		</svg>
		{#if $num > 0}
		<span class="badge badge-primary">{$num}</span>
		{/if}
	</button>
	{#if 0!=0}
	<button class="btn btn-round btn-badge" on:click={notes.toggle} title="Notes ({$notes ? 'ON' : 'OFF'})">
		<svg class="icon-outline" xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor">
			<path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M15.232 5.232l3.536 3.536m-2.036-5.036a2.5 2.5 0 113.536 3.536L6.5 21.036H3v-3.572L16.732 3.732z" />
		</svg>

		<span class="badge tracking-tighter" class:badge-primary={$notes}>{$notes ? 'ON' : 'OFF'}</span>
	</button>
	{/if}

</div>


<style>
	.action-buttons {
			@apply flex flex-wrap justify-evenly self-end;
		}
	
		.btn-badge {
			@apply relative;
		}
	
		.badge {
			min-height: 20px;
			min-width:  20px;
			@apply p-1 rounded-full leading-none text-center text-xs text-white bg-gray-600 inline-block absolute top-0 left-0;
		}
	
		.badge-primary {
			@apply bg-primary;
		}
		
	

	
</style>


