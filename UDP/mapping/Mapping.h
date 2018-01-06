#pragma once
#include <map>
#include <string>
#include "CM.h"
#include "Mem.h"
#include <iostream>

class Mapping
{
public:
	static std::map<char*, CM> Mapping::lookup;
	
	Mapping() {
		setup();
	}

	static CM getClass(const char* key) {
		return lookup.at((char*)key);
	}

	static const char* getClassName(const char* key) {
		return getClass(key).name;
	}
private:
	static void setup() {
		// base - normal jvm classes
		struct CM m = make("List", "java/util/List");
		method(m, "get", "(I)Ljava/lang/Object;", false);
		method(m, "toArray", "()[Ljava/lang/Object;", false);
		method(m, "size", "()I", false);
		m = make("Set", "java/util/Set");
		method(m, "toArray", "()[Ljava/lang/Object;", false);
		method(m, "size", "()I", false);
		// obfuscated minecraft classes - 1.12
		m = make("Entity", "ve");
		field(m, "x", "p", "D", false);
		field(m, "y", "q", "D", false);
		field(m, "z", "r", "D", false);
		method(m, "getID", "S", "()I", false);
		method(m, "getName", "h_", "()Ljava/lang/String;", false);
		m = make("WorldClient", "brz");
		field(m, "entities", "K", "Ljava/util/Set;", false);
		method(m, "setTime", "b", "(J)V", false);
		m = make("PlayerSP", "bub");
		field(m, "x", "p", "D", false);
		field(m, "y", "q", "D", false);
		field(m, "z", "r", "D", false);
		field(m, "yaw", "v", "F", false);
		field(m, "pitch", "w", "F", false);
		method(m, "getID", "S", "()I", false);
		method(m, "getName", "h_", "()Ljava/lang/String;", false);
		method(m, "setSprint", "f", "(Z)V", false);
		m = make("Minecraft", "bhz");
		field(m, "player", "h", "Lbub;", false);
		field(m, "world", "f", "Lbrz;", false);
		method(m, "getMinecraft", "z", "()Lbhz;", true);
	}

	static void field(CM cm, char* name, char* desc, bool isStatic) {
		field(cm, name, name, desc, isStatic);
	}

	static void method(CM cm, char* name, char* desc, bool isStatic) {
		method(cm, name, name, desc, isStatic);
	}

	static void field(CM cm, char* keyName, char* obName, char* desc, bool isStatic) {
		cm.fields.insert(std::make_pair(keyName, Mem(obName, desc, isStatic)));
	}

	static void method(CM cm, char* keyName, char* obName, char* desc, bool isStatic) {
		cm.methods.insert(std::make_pair(keyName, Mem(obName, desc, isStatic)));
	}

	static CM make(char* key, char* name) {
		struct CM cm(name);
		lookup.insert(std::make_pair(key, cm));
		return cm;
	}
};