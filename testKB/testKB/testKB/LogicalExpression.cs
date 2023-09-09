using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace testKB
{
    public class LogicalExpression
    {
        private string _symbol;
        private string _connective;
        private List<LogicalExpression> _children = new List<LogicalExpression>();
        private string _original;

        public LogicalExpression(string sentence)
        {

            _original = sentence;
            sentence = sentence.Trim();
            if (sentence.Contains("<=>") || sentence.Contains("=>") || sentence.Contains("&") || sentence.Contains("~") || sentence.Contains("\\/"))
            {
                SentenceParser(sentence);
                Console.WriteLine("new sentence: " + sentence);
            }
            else
            {
                Console.WriteLine("symbol sentence: " + sentence);
                _symbol = sentence;
            }
        }

        public LogicalExpression()
        {

        }


        public List<LogicalExpression> Children
        {
            get { return _children; }
            set { _children = value; }
        }

        public void printInfo()
        {
            Console.WriteLine("Original String: " + _original);
            if (_symbol is null)
            {
                if (_children.Count > 1)
                {
                    Console.WriteLine("left: " + _children[0].OriginalString + " Connective: " + _connective + " right: " + _children[1].OriginalString);
                    foreach (LogicalExpression child in _children)
                    {
                        child.printInfo();
                    }
                }
                else if (_children.Count == 1)
                {
                    _children[0].printInfo();
                }


            }
            else
            {
                Console.WriteLine("Symbol: " + _symbol);
            }
        }
        public string Connective
        {
            get { return _connective; }
            set { _connective = value; }
        }
        public string Symbol
        {
            get { return _symbol; }
        }

        public string OriginalString
        {
            get { return _original; }
        }

        public void SentenceParser(string sentence)
        {
            int bracketCounter = 0;
            int operatorIndex = -1;
            bool trigger = true;
            bool trigger2 = true;
            sentence.Trim();
            Console.WriteLine("Initial Sentence: " + sentence);
            //Console.Write("OperatorIndex: "+ operatorIndex + "\n");
            for (int i = 0; i < sentence.Length; i++)
            {
                char c = sentence.ElementAt(i);
                if (c == '(')
                {
                    //Console.WriteLine(bracketCounter);
                    bracketCounter = bracketCounter + 1;

                }
                else if (c == ')')
                {
                    bracketCounter--;
                    //Console.WriteLine(bracketCounter);
                }
                else if ((c == '<') && bracketCounter == 0)
                {
                    //Console.WriteLine("bracketCounter should be 0: " + bracketCounter);
                    operatorIndex = i;
                    trigger = false;
                    trigger2 = false;
                }
                else if ((c == '=' && c + 1 == '>') && bracketCounter == 0 && trigger2)
                {
                    operatorIndex = i;
                    trigger = false;
                    trigger2 = false;
                }
                else if ((c == '&') && bracketCounter == 0 && trigger && trigger2)
                {
                    operatorIndex = i;
                    trigger = false;
                    trigger2 = false;
                }
                else if (c == '\\' && bracketCounter == 0 && trigger && trigger2)
                {
                    operatorIndex = i;
                    trigger = false;
                    trigger2 = false;
                }
                else if (c == '~' && bracketCounter == 0 && operatorIndex < 0 && trigger && trigger2)
                {
                    operatorIndex = i;
                }

            }
            //Console.WriteLine("op: " +operatorIndex);
            if (operatorIndex < 0)
            {
                sentence = sentence.Trim();
                if (sentence.ElementAt(0) == '(' && sentence.ElementAt(sentence.Length - 1) == ')')
                {
                    SentenceParser(sentence.Substring(1, sentence.Length - 2));
                }
            }


            else
            {
                //Console.WriteLine("Entering Else");
                //Console.WriteLine(sentence);
                if (sentence.ElementAt(operatorIndex) == '<')
                {
                    Console.WriteLine("sentence: " + sentence);
                    string first = sentence.Substring(0, operatorIndex);
                    string second = sentence.Substring(operatorIndex + 3);
                    first = first.Trim();
                    second = second.Trim();
                    LogicalExpression child1 = new LogicalExpression(first);
                    LogicalExpression child2 = new LogicalExpression(second);
                    _children.Add(child1);
                    _children.Add(child2);
                    _connective = "<=>";

                }
                else if (sentence.ElementAt(operatorIndex) == '=')
                {

                    string first = sentence.Substring(0, operatorIndex);
                    string second = sentence.Substring(operatorIndex + 2);
                    first = first.Trim();
                    second = second.Trim();
                    LogicalExpression child1 = new LogicalExpression(first);
                    LogicalExpression child2 = new LogicalExpression(second);
                    _children.Add(child1);
                    _children.Add(child2);
                    _connective = "=>";
                }
                else if (sentence.ElementAt(operatorIndex) == '&')
                {
                    string first = sentence.Substring(0, operatorIndex);
                    string second = sentence.Substring(operatorIndex + 1);
                    first = first.Trim();
                    second = second.Trim();
                    LogicalExpression child1 = new LogicalExpression(first);
                    LogicalExpression child2 = new LogicalExpression(second);
                    _children.Add(child1);
                    _children.Add(child2);
                    _connective = "&";

                }
                else if (sentence.ElementAt(operatorIndex) == '\\')
                {

                    string first = sentence.Substring(0, operatorIndex);
                    string second = sentence.Substring(operatorIndex + 2);
                    first = first.Trim();
                    second = second.Trim();
                    LogicalExpression child1 = new LogicalExpression(first);
                    LogicalExpression child2 = new LogicalExpression(second);
                    _children.Add(child1);
                    _children.Add(child2);
                    _connective = "\\/";

                }
                else if (sentence.ElementAt(operatorIndex) == '~')
                {
                    string first = sentence.Substring(operatorIndex + 1);
                    first = first.Trim();
                    LogicalExpression child = new LogicalExpression(first);
                    _children.Add(child);
                    _connective = "~";
                }
                //else
                //{
                //    _symbol = sentence;
                //    _connective = null;
                //    _children = null;
                //}

            }

        }
    }
}