// @category LithTech
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;
import java.io.*;
import java.util.*;
public class ExportC extends GhidraScript {
  public void run() throws Exception {
    // 1. apply renames
    try (BufferedReader br = new BufferedReader(new FileReader("/home/claude/rename.tsv"))) {
      String l; while ((l = br.readLine()) != null) {
        String[] p = l.split("\t"); if (p.length < 3) continue;
        Function f = getFunctionAt(toAddr("0x"+p[0]));
        if (f == null) f = createFunction(toAddr("0x"+p[0]), null);
        if (f == null) continue;
        setPlateComment(f.getEntryPoint(), "repo: " + p[2]);
        if (f.getName().startsWith("FUN_")) f.setName(p[1], SourceType.USER_DEFINED);
      }
    }
    // 2. decompile everything
    DecompInterface di = new DecompInterface(); di.openProgram(currentProgram);
    File outDir = new File("/mnt/user-data/outputs/lt_re/c"); outDir.mkdirs();
    Map<String,PrintWriter> w = new HashMap<>();
    int n = 0, ok = 0;
    for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
      if (monitor.isCancelled()) break;
      if (f.isThunk() || f.isExternal()) continue;
      n++;
      String nm = f.getName(), mod;
      java.util.regex.Matcher m = java.util.regex.Pattern.compile("^(.+)_[0-9a-f]{6,8}$").matcher(nm);
      mod = m.matches() ? m.group(1) : String.format("unnamed_%04x", f.getEntryPoint().getOffset() >> 16);
      PrintWriter pw = w.get(mod);
      if (pw == null) { pw = new PrintWriter(new FileWriter(new File(outDir, mod + ".c"))); pw.println("/* lithtech.exe decompilation - module " + mod + " */\n#include \"ghidra_types.h\"\n"); w.put(mod, pw); }
      DecompileResults r = di.decompileFunction(f, 60, monitor);
      pw.println("/* " + f.getEntryPoint() + " size=" + f.getBody().getNumAddresses() + (r.decompileCompleted() ? "" : " DECOMPILE FAILED") + " */");
      if (r.decompileCompleted()) { pw.println(r.getDecompiledFunction().getC()); ok++; }
      else pw.println("/* " + r.getErrorMessage() + " */\n");
      pw.flush();
      if (n % 200 == 0) println("decompiled " + n);
    }
    for (PrintWriter p : w.values()) p.close();
    println("DONE functions=" + n + " ok=" + ok);
  }
}
