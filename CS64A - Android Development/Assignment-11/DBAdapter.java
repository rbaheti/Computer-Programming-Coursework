package com.example.databaseapp;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.os.Build;

/**
 * Created by rashmi on 3/21/2017.
 */

public class DBAdapter {
    public static final String DATABASE_NAME = "MYDB";
    public static final String DATABASE_TABLE = "MyDBTable";
    public static final int DATABASE_VERSION = 1;

    public static final String KEY_ROWID = "_id";
    public static final String KEY_MAJOR= "major";
    public static final String KEY_NAME = "name";

    public static final int COL_ROWID = 0;
    public static final int COL_NAME = 1;
    public static final int COL_MAJOR = 2;

    public static final String[] ALL_KEYS = {KEY_ROWID, KEY_MAJOR, KEY_NAME};

    private Context context;
    private SQLiteDatabase db;
    private DatabaseHelper myDBHelper;

    DBAdapter(Context context){
        this.context = context;
        myDBHelper = new DatabaseHelper(context);
    }

    public DBAdapter open(){
        db = myDBHelper.getWritableDatabase();
        return this;
    }

    public void close(){
        myDBHelper.close();
    }


    public long insertRow(String name, String major){
        ContentValues values = new ContentValues();
        values.put(KEY_NAME, name);
        values.put(KEY_MAJOR, major);
        long rowid = db.insert(DATABASE_TABLE, null, values);
        return rowid;
    }

    public Cursor getAllRows(){
        Cursor cursor = db.query(DATABASE_TABLE, ALL_KEYS, null, null, null, null, null);
        if(cursor.getCount() > 0){
            cursor.moveToFirst();
        }
        return cursor;
    }

    public boolean deleteRow(long rowid){
        String whereStr = KEY_ROWID +"="+rowid;
        return (db.delete(DATABASE_TABLE, whereStr, null) > 0);
    }

    public void deleteAll(){
        Cursor cursor = getAllRows();
        int rowidx = cursor.getColumnIndexOrThrow(KEY_ROWID);
        if(cursor.getCount()>0){
            cursor.moveToFirst();
            do{
                deleteRow(cursor.getLong(rowidx));
            }while(cursor.moveToNext());
        }
    }

    public Cursor getRow(long rowid){
        String whereStr =  KEY_ROWID +"="+rowid;
        Cursor cursor = db.query(DATABASE_TABLE, ALL_KEYS, whereStr, null, null, null, null);
        if(cursor.getCount() > 0){
            cursor.moveToFirst();
        }
        return cursor;
    }

    class DatabaseHelper extends SQLiteOpenHelper {

        // constructor
        public DatabaseHelper(Context context) {
            super(context, DATABASE_NAME, null, DATABASE_VERSION);
        }

        public void onCreate(SQLiteDatabase database){
            String CREATE_DB_SQL = "CREATE TABLE " + DATABASE_TABLE + "("
                    + KEY_ROWID + " integer primary key autoincrement, "
                    + KEY_NAME + " text not null, "
                    + KEY_MAJOR + " text not null );";

            database.execSQL(CREATE_DB_SQL);
        }

        public void onUpgrade(SQLiteDatabase database, int oldversion, int newversion){
            database.execSQL("DROP TABLE IS EXISTS " + DATABASE_TABLE);
            onCreate(database);
        }
    }
}
