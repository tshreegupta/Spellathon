package com.example.tanushree.spellathon;

public class MyNDK {

   static
   {
      System.loadLibrary("driver");
   }
   public native String getMyString();
}
