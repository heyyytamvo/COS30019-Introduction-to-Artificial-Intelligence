using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Text;
using System.Threading.Tasks;

namespace testKB
{
    class Program
    {
        

        /*
         * Main entry point for program.
         */
        static void Main(string[] args)
        {
            //if (ReadProblem(args[1], args[0]))
            //{
            //    //Determines which algorithm to use for solving problem
            //    switch (args[0])
            //    {
            //        case ("TT"):
            //            _engine = new TruthTable(_kb, _query);
            //            break;
            //        case ("BC"):
            //            _engine = new BackwardChaining(_kb, _query);
            //            break;
            //        case ("FC"):
            //            _engine = new ForwardChaining(_kb, _query);
            //            break;
            //        case ("GTT"):
            //            _engine = new ExtendedTruthTable(_akb, _query);
            //            break;
            //        case ("DPLL"):
            //            _engine = new DPLL();
            //            break;
            //        default:
            //            throw new System.ArgumentException("No Valid Inference Method Given");
            //    }
            //}
            Console.WriteLine("Hello em");
            string testLogicalExpression = "(a <=> (c => ~d)) & b & (b => a)";
            LogicalExpression test = new LogicalExpression(testLogicalExpression);
            //Console.WriteLine(test.Connective);
            //Console.WriteLine(test.OriginalString);
            Console.WriteLine("___________________");
            test.printInfo();
        }

    


    }
}
