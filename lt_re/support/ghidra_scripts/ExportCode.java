// @category LithTech
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import java.io.*;
public class ExportCode extends GhidraScript {
  public void run() throws Exception {
    try (PrintWriter pw = new PrintWriter(new FileWriter("/tmp/code_units.txt"))) {
      long n = 0;
      for (Instruction i : currentProgram.getListing().getInstructions(true)) { pw.println(Long.toHexString(i.getAddress().getOffset()) + " " + i.getLength()); n++; }
      println("instructions " + n);
    }
  }
}
