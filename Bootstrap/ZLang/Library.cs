// .cs
// Z Library Compiler Class
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
	/** Compiles .zcode into a .zlib library binary. */
	public sealed class Library
	{
		Bytecode output;
		AbstractSyntaxTree ast;

		/** Constructor. */
		public Library()
		{
			output = new();
			ast = new();
		}
	}
}
