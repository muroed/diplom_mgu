//C++ 3.1		Листинг #4			MS-DOS		Рисование графика функции y = x * x	
#include <iostream>
// #include <conio>
#include <graphics>
#include <math.h>

int main(){
   clrscr();


   double start = -150;	//Начальная точка по X
   double end = 151;	//Конечная точка по X
   int stepx = 15;		//Добавили шаг для хода по оси X
   int stepy = 15;		//Добавили шаг для хода по оси Y

   const unsigned MAX = fabs(start) + fabs(end);	//Вычисляемое значение для задания ёмкоси массиву точек
   double *y = new double[MAX];						//Создаём массив нужной ёмкости

   unsigned index = 0;
   for (int i=start; i<end; i++){
      y[index] = (i * i * -1);			//С помощью формулы вычисляем значения и записываем их в массив
      //y[index] = sin(i) * -1;			//так можно нарисовать y=sin(x)
      index++;
   }


   int gr = DETECT, gm;
   initgraph(&gr, &gm, "");

   double OX = getmaxx()/2;			//Находим точки центра экрана
   double OY = getmaxy()/2;

  //Эта часть кода только для нарисования оси ординат
     setcolor(RED);
     setlinestyle(DOTTED_LINE,1,1);
     line(0, getmaxy()/2, getmaxx(), getmaxy()/2);
     line(getmaxx()/2, 0, getmaxx()/2, getmaxy());
     setlinestyle(SOLID_LINE,1,1);
     setcolor(WHITE);


   //Эта часть для рисования графика
      int dx = stepx;		//Определяемся с шагом по каждой из осей
      int dy = stepy;
      int y_;				//это точка по Y (сам массив с точками, т. е. y[] менять неправильно, следует использовать доп.переменную)
	  
      moveto(OX - fabs(start) * dx, y[0] + OY);		//устанавливаемся в точку начала рисования графика
      double x = fabs(start) * -dx;					//учитывая, что у нас есть шаг, корректируем позицию стартовой точки
      for (i=0; i<MAX; i++){
		 y_ = y[i] * dy;				//для вычисленного y корректируемся на шаг, определённый для Y
		 lineto(x+OX, y_+OY);			//проводим линию
		 x+=dx;							//делаем шаг по X
      }

   cin.get();
   closegraph();
   return 0;
}