// @category LithTech
import ghidra.app.script.GhidraScript;
import ghidra.program.model.data.*;
import java.io.*;
import java.util.*;
public class ExportTypes extends GhidraScript {
  public void run() throws Exception {
    DataTypeManager dtm = currentProgram.getDataTypeManager();
    List<DataType> l = new ArrayList<>();
    Iterator<DataType> it = dtm.getAllDataTypes();
    while (it.hasNext()) { DataType d = it.next();
      if (d.getCategoryPath().toString().startsWith("/Demangler") || d instanceof BuiltInDataType) continue; l.add(d); }
    try (FileWriter fw = new FileWriter("/mnt/user-data/outputs/lt_re/c/lt_types.h")) {
      DataTypeWriter w = new DataTypeWriter(dtm, fw);
      w.write(l, monitor);
    }
    println("types written " + l.size());
  }
}
