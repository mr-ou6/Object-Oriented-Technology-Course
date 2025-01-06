<script>
  import Candidates from "./Candidates.svelte";
  import { SUDOKU_SIZE } from "@sudoku/constants";
  import { cursor } from "@sudoku/stores/cursor";
  import { Gridsource } from "@sudoku/stores/grid";
  import { currentValueStore, num } from "@sudoku/stores/currentValueStore";
  import { userGrid } from "@sudoku/stores/grid";
  import { candidates } from "@sudoku/stores/candidates";
  import { modal } from "@sudoku/stores/modal";

  export let value;
  export let cellX;
  export let cellY;
  export let candidates1;
  export let hintsLevel;

  export let disabled;
  export let conflictingNumber;
  export let userNumber;
  export let selected;
  export let sameArea;
  export let sameNumber;

  

  const borderRight = cellX !== SUDOKU_SIZE && cellX % 3 !== 0;
  const borderRightBold = cellX !== SUDOKU_SIZE && cellX % 3 === 0;
  const borderBottom = cellY !== SUDOKU_SIZE && cellY % 3 !== 0;
  const borderBottomBold = cellY !== SUDOKU_SIZE && cellY % 3 === 0;


  let lastClickTime = 0;
  let timeoutId = null;

  $: if (conflictingNumber) {
    modal.show("nosolution",
    {
      //传递必要的数据给 NoSolution 组件

      data: {
          callback: () => {
            // 点击继续后的回调函数
            conflictingNumber = false; // 重置冲突状态
            console.log("errrr", conflictingNumber);
          },

      },
    }
    );

  }

  // 统一的点击事件处理
  function handleClick(event) {
    cursor.set(cellX - 1, cellY - 1);
    const currentTime = Date.now();
    const timeDiff = currentTime - lastClickTime;

    if (timeDiff < 300) {
      // 判断是否为双击
      clearTimeout(timeoutId); // 清除单击的延时
      handleDoubleClick(event);
    } else {
      // 如果是单击
      timeoutId = setTimeout(() => {
        handleSingleClick(event);
      }, 300); // 延时300ms处理单击事件
    }

    lastClickTime = currentTime; // 更新最后点击时间
  }

  function handleSingleClick(event) {
    
    console.log("单击事件触发");
    // 处理单击事件逻辑
    cursor.set(cellX - 1, cellY - 1);
    console.log($cursor.y);
    let isUpdating = false; // 标志位，避免重复更新
    Gridsource.subscribe(($Gridsource) => {
      if(isUpdating)return;
      if ($cursor.y !== null) {
        const currentValue = $Gridsource[$cursor.y][$cursor.x];
        console.log("Current Value in Child:", currentValue);
        currentValueStore.set(currentValue); // 更新 store 中的值
      }
      isUpdating=true;
    });
  }



  function handleDoubleClick(event) {
    cursor.set(cellX - 1, cellY - 1);
    event.stopPropagation(); // 阻止事件冒泡，防止父级事件处理

    let isUpdating = false;
    
    // if (
    //   $userGrid[$cursor.y][$cursor.x] === 0 &&
    //   candidates1 &&
    //   candidates1.length === 1
    // ) {
    //   console.log("双击事件触发");
    //   console.log("111");
    //   userGrid.set($cursor, candidates1[0]); // 更新 grid
    //   let pos = { x: $cursor.x, y: $cursor.y };
    //   console.log($userGrid[$cursor.y][$cursor.x]);
    //   // let a_xhr = userGrid.candidateonlySet;
    //   // 已知 userGrid.candidateonlySet 是 writable(new Set())，根据注释内容，完成从candidateonlySet中删去当前cursor的y和x
    //   // 考虑没有has

    //   let candidateOnlySet;
    //   console.log(userGrid)
    //   console.log($userGrid.candidateOnlySet)
    //   $userGrid.candidateOnlySet.subscribe(value => {
    //     candidateOnlySet = value;
    //   });

    //   // const candidateOnlySet = userGrid.candidateonlySet;
    //   if (candidateOnlySet instanceof Set) {
    //       // 判断当前 cursor 对应的坐标元素是否存在于集合中，若存在则删除
    //       const elementToRemove = `${$cursor.y},${$cursor.x}`;
    //       if (candidateOnlySet.has(elementToRemove)) {
    //           candidateOnlySet.delete(elementToRemove);
    //       }
    //       if (candidateOnlySet.size === 0) {
    //           console.log("22222222222222222");
    //           userGrid.applyHint($cursor);
    //       }
    //   } else {
    //       // 如果不是 Set 类型，这里可以根据实际需求进行适当的错误处理或日志记录等操作
    //       console.error("userGrid.candidateonlySet is not a Set type as expected!");
    //   }






      // userGrid.candidateonlySet.subscribe(($candidateonlySet) => {
      //   if ($candidateonlySet.has(`${$cursor.y},${$cursor.x}`)) {
      //     $candidateonlySet.delete(`${$cursor.y},${$cursor.x}`);
      //     //console.log( `${$cursor.y},${$cursor.x}`,"已删除");
      //   }
      //   if ($candidateonlySet.size===0){
      //     console.log("22222222222222222");
      //     userGrid.applyHint($cursor);
      //   }
      // });

      //candidates.subscribe($candidates=> {
      //console.log($cursor.x+','+$cursor.y,$candidates[$cursor.x+','+$cursor.y]);
      // console.log($cursor.y+','+$cursor.x,$candidates[$cursor.y+','+$cursor.x]);
      //});
      //删除候选值
    //   candidates.clear(pos);
    //   //双击清空推断
    //   currentValueStore.set("");
    // }

    //

    /*
    let func = ()=>{
      aaa.unsubscribe(func);
    };
    aaa.subscribe(func);

    */

    userGrid.subscribe(($userGrid) => {
      // console.log("xhr_1")
      // console.log($num);
      if(isUpdating)return;
      if ($num === -1){
        return
      }
      if (
        $userGrid[$cursor.y][$cursor.x] === 0 &&
        candidates1 &&
        candidates1.length === 1
      ) {
        // console.log("双击事件触发");
        // console.log("111");

        userGrid.set($cursor, candidates1[0]); // 更新 grid
        isUpdating=true;
        let pos = { x: $cursor.x, y: $cursor.y };
        // console.log($userGrid[$cursor.y][$cursor.x]);
        let isHinting = false;  // 防止重复调用提示逻辑

        userGrid.candidateonlySet.subscribe(($candidateonlySet) => {
          // console.log("xhr_2")
          // console.log($num);
          if(isHinting)return;
          if ($num === -1){
            return
          }
          if ($candidateonlySet.has(`${$cursor.y},${$cursor.x}`)) {
            $candidateonlySet.delete(`${$cursor.y},${$cursor.x}`);
            //console.log( `${$cursor.y},${$cursor.x}`,"已删除");
          }
          if ($candidateonlySet.size===0 && $num > 0){
            // console.log($candidateonlySet.size,$num);
            userGrid.applyHint($cursor);
          }
          isHinting = true;
        });

        //candidates.subscribe($candidates=> {
        //console.log($cursor.x+','+$cursor.y,$candidates[$cursor.x+','+$cursor.y]);
        // console.log($cursor.y+','+$cursor.x,$candidates[$cursor.y+','+$cursor.x]);
        //});
        //删除候选值
        candidates.clear(pos);
        //双击清空推断
        currentValueStore.set("");
      }
    });
  }
</script>

<div
  class="cell row-start-{cellY} col-start-{cellX}"
  class:border-r={borderRight}
  class:border-r-4={borderRightBold}
  class:border-b={borderBottom}
  class:border-b-4={borderBottomBold}
>
  {#if !disabled}
    <div
      class="cell-inner"
      class:user-number={userNumber}
      class:selected
      class:same-area={sameArea}
      class:same-number={sameNumber}
      class:conflicting-number={conflictingNumber}
    >
      <button
        class="cell-btn"
        on:click={handleClick}
        class:showhighlight={candidates1 && candidates1.length === 1}
      >
        {#if candidates1 && candidates1.length > 1 && hintsLevel >= $num && $num >= candidates1.length}
          <Candidates {candidates1} {cellY} {cellX} />
        {:else}
          <span
            class="cell-text"
            class:showhigh={candidates1 && candidates1.length === 1}
            >{candidates1 && candidates1.length === 1
              ? candidates1[0]
              : value || ""}</span
          >
        {/if}
      </button>
    </div>
  {/if}
</div>

<style>
  .cell {
    @apply h-full w-full row-end-auto col-end-auto;
  }

  .cell-inner {
    @apply relative h-full w-full text-gray-800;
  }

  .cell-btn {
    @apply absolute inset-0 h-full w-full;
  }

  .cell-btn:focus {
    @apply outline-none;
  }

  .cell-text {
    @apply leading-full text-base;
  }
  .showhigh {
    @apply leading-full text-white;
  }
  .showhighlight {
    background: rgba(0, 255, 0, 0.3); /* 去掉背景 */
  }
  @media (min-width: 300px) {
    .cell-text {
      @apply text-lg;
    }
  }

  @media (min-width: 350px) {
    .cell-text {
      @apply text-xl;
    }
  }

  @media (min-width: 400px) {
    .cell-text {
      @apply text-2xl;
    }
  }

  @media (min-width: 500px) {
    .cell-text {
      @apply text-3xl;
    }
  }

  @media (min-width: 600px) {
    .cell-text {
      @apply text-4xl;
    }
  }

  .user-number {
    @apply text-primary;
  }

  .selected {
    @apply bg-primary text-white;
  }

  .same-area {
    @apply bg-primary-lighter;
  }

  .same-number {
    @apply bg-primary-light;
  }

  .conflicting-number {
    @apply text-red-600;
  }
</style>
