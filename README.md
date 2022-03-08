# Double-ended Priority Queue
Max Heap, Double-ended Heap(DEAP) and Min-Max Heap. 

Language: C++
## How to use: 
Enter Your command([0] Quit [1] Max Heap [2] DEAP [3] MinMax Heap). After you enter your command, enter your input fileNum(ex: For "input101.txt" please enter "101").

*noted: my code uses "number of studnets" as key value.*



## 簡介：
(a) 讀入資料：

一個字元一個字元抓，把所有字元存進string content裡面，直到讀到第6個tab，也就是代表接下來直到下個tab為止的字元都屬於number of students。將number of student分開存，就繼續將剩下的字元讀入content裡，直到此行結束。對每行input都執行上述的步驟。

(b) 任務一(Max Heap)：

將剛剛的資料一筆一筆Maxinsert()進heapTree裡面，進去後此新的node會跟自己的parent比較，如果比parent大的話就swap，重複此步驟直到抵達root或是新node不比parent大。

實作上主要困難在於作此程式時我只排序index，然後在compare大小時在用那個index去collegeSet裡面找numStudent，而不是設一個struct裡面有index和key，所以出了一堆問題。所以最後在寫下個任務時我就學乖不用這個方式寫了。

(c) 任務二(DEAP)：

將剛剛的資料一筆一筆DeapInsert()進deapTree裡面，進去之後先判斷位置在minHeap還是maxHeap：如果在maxHeap就先去找minHeap中對應的node，然後如果新進的值比對應node小，就跟對應node替換後在minHeap裡面做minHeapify；如果新進的值比對應node大，就直接maxHeapify。如果在minHeap就先去找maxHeap中對應的node(先找父節點)，然後如果新進的值比對應node大，就跟對應node替換後在maxHeap裡面做maxHeapify；如果新進的值比對應node小，就直接minHeapify。

原本以為實作起來會跟maxHeap差不多簡單，不過在尋找另一半Heap中對應的node時出了很多很多的困難，使得完成DEAP的過程變得非常不輕鬆。好險最後在限時搶答看到同學回答，瞬間激起我的回憶、釐清我的邏輯，才得以順利寫出來。

(d) 任務三(MinMax Heap)：

一筆一筆加入資料，並在每筆資料加入時，都依加入的位置，判斷其是在min還是max層，再依此調整其位置(heapify)使min-max heap符合規則後，再加入下一筆資料。(其中動作都類似上面提到的DEAP)

原本我想直接使用DEAP的程式碼去做更改，實作出MinMax Heap，不過實際做之後發現我的DEAP實在是做得太怪了，最後幾乎算是重寫了整個MinMax Heap(主要問題是發生在我DEAP的index紀錄跟MinMax Heap的不太一樣，因為DEAP的開頭node是不用放東西的)。

## 圖示：
![image](https://github.com/PBoy20511/Double-ended-Priority-Queue/blob/main/temp/任務一MaxHeap流程圖.jpg)
![image](https://github.com/PBoy20511/Double-ended-Priority-Queue/blob/main/temp/任務二DEAP流程圖.jpg)

## 提問：任務一和任務二的執行效率如何比較？
解說：

![image](https://github.com/PBoy20511/Double-ended-Priority-Queue/blob/main/temp/messageImage_1646709323512.jpg)
(swap次數/總資料筆數)

任務一比任務二的效率好。我想這是因為任務二的目的是要實現”Double-ended”這項特性，讓未來使用者在取出最小值和最大值時的速度都可以一樣快，才決定犧牲掉一點建立樹的時間(totally worth it)。
