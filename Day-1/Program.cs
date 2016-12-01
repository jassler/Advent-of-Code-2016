using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading.Tasks;
using System.Text.RegularExpressions;



namespace Day1
{


    struct Move
    {
        public char dir;
        public int steps;

        public Move(char _dir, int _steps)
        {
            if (_dir != 'L' && _dir != 'R')
                throw new Exception("Direction is not 'L'eft or 'R'ight");
            dir = _dir;
            steps = _steps;
        }


    }

    class Pos
    {
        public int x;
        public int y;
        // dir[0] -> x-Dir
        // dir[1] -> y-Dir
        int[] dir = { 1, 0 };
        
        public Pos(int _x, int _y)
        {
            x = _x;
            y = _y;
        }

        public void Move(Move m)
        {
            int mul = (m.dir == 'L') ? 1 : -1;
            if (dir[0] == 0)
            {
                dir[0] -= mul * dir[1];
                dir[1] += mul * dir[0];
            }
            else
            {
                dir[1] += mul * dir[0];
                dir[0] -= mul * dir[1];
            }

            x += dir[0] * m.steps;
            y += dir[1] * m.steps;
        }

        public int GetDistance()
        {
            return Math.Abs(x) + Math.Abs(y);
        }
    }

    class Program
    {
        static List<Move> movements = new List<Move>();

        static void ReadInput(string filename)
        {
            movements.Clear();
            try
            {
                using (StreamReader sr = new StreamReader(filename))
                {
                    string[] instructions = Regex.Replace(sr.ReadLine(), @"\s+", "").Split(',');
                    foreach (String s in instructions)
                    {
                        try
                        {
                            movements.Add(new Move(s[0], int.Parse(s.Substring(1))));
                        } catch(Exception e)
                        {
                            Console.WriteLine("Error when converting instruction: {0}", e.Message);
                        }
                    }
                        
                }
            } catch(Exception e)
            {
                Console.WriteLine("Error when reading textfile: {0}", e.Message);
            }
        }


        static void Main(string[] args)
        {
            ReadInput("C:\\Users\\Felix Fritz\\Documents\\Visual Studio 2015\\Projects\\Day1\\Day1\\Day1_Input.txt");
            Pos myPos = new Pos(0,0);
            foreach(Move m in movements)
            {
                myPos.Move(m);
            }

            Console.WriteLine("Position: x = {0} | y = {1}", myPos.x, myPos.y);
            Console.WriteLine("Distance: {0}", myPos.GetDistance());
            Console.Read();
        }
    }
}
