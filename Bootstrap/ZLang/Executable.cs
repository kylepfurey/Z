// .cs
// Z Executable Compiler Class
// by Kyle Furey

using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ZLang
{
	/** Compiles .zcode into a .zac executable binary. */
	public sealed class Executable
	{
		Bytecode output;
		AbstractSyntaxTree ast;

		/** Constructor. */
		public Executable()
		{
			output = new();
			ast = new();
		}
	}
}
