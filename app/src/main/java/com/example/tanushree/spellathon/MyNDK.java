package com.example.tanushree.spellathon;

public class MyNDK {

   static
   {
      System.loadLibrary("driver");
   }
   //native function declaration
   public native String getMyString(String str);
   public native void dictionary();

}
