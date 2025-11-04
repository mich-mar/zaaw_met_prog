#include <iostream>
#include <dlfcn.h>    
#include <cassert>
#include <string>
#include <sstream>
#include <cstdio>
#include <stdexcept>
#include <fstream>
#include <map>        
#include <list>         
#include "AbstractInterp4Command.hh"
#include "preprocesor.hh" 

/*
 * Type definitions for function pointers from the libraries
 * This makes the code more readable.
 */
// Pointer to the function creating a command object
using Fun_CreateCmd = AbstractInterp4Command* (*)(void);
// Pointer to the function getting the command name
using Fun_GetCmdName = const char* (*)(void);


int main()
{
  // ====================================================================
  // 1. Definition of interpreter data structures (Task 1.2)
  // ====================================================================

  // Map storing the association between a command name (e.g., "Move")
  // and the function that creates an object of that command (CreateCmd).
  std::map<std::string, Fun_CreateCmd> CommandMap;

  // List storing handles to the open libraries,
  // so they can be properly closed at the end of the program.
  std::list<void*> LibraryHandles;

  // List of libraries to load.
  std::list<std::string> LibraryNames = {
    "libInterp4Rotate.so",
    "libInterp4Move.so",
    "libInterp4Pause.so",
    "libInterp4Set.so"
  };

  std::cout << "--- LOADING PLUGINS ---" << std::endl;

  // ====================================================================
  // 2. Plugin loading loop
  // ====================================================================
  
  for (const std::string& LibraryName : LibraryNames) {
    void* pLibraryHandle = dlopen(LibraryName.c_str(), RTLD_LAZY);

    if (!pLibraryHandle) {
      std::cerr << "!!! ERROR: Could not open library: " << LibraryName << std::endl;
      std::cerr << "!!!   " << dlerror() << std::endl;
      continue; // Move to the next library
    }

    // Get pointer to the GetCmdName function
    void* pFun_GetCmdName = dlsym(pLibraryHandle, "GetCmdName");
    if (!pFun_GetCmdName) {
      std::cerr << "!!! ERROR: Could not find function GetCmdName in " << LibraryName << std::endl;
      dlclose(pLibraryHandle);
      continue;
    }
    Fun_GetCmdName GetName = reinterpret_cast<Fun_GetCmdName>(pFun_GetCmdName);

    // Get pointer to the CreateCmd function
    void* pFun_CreateCmd = dlsym(pLibraryHandle, "CreateCmd");
    if (!pFun_CreateCmd) {
      std::cerr << "!!! ERROR: Could not find function CreateCmd in " << LibraryName << std::endl;
      dlclose(pLibraryHandle);
      continue;
    }
    Fun_CreateCmd CreateCommand = reinterpret_cast<Fun_CreateCmd>(pFun_CreateCmd);

    // We have everything. Get the name and add it to the map.
    std::string CommandName = GetName();
    CommandMap[CommandName] = CreateCommand;
    
    // Store the handle to be closed later
    LibraryHandles.push_back(pLibraryHandle);

    std::cout << "  Loaded command: " << CommandName << std::endl;
  }


  // ====================================================================
  // 3. Preprocessor Test
  // ====================================================================
  
  std::cout << "\n--- TESTING PREPROCESSOR ---" << std::endl;
  
  const char* testFilename = "test_preproc.spr";
  std::stringstream CommandStream; // Stream to store the preprocessor output
  
  // 3.1. Check if the test file exists
  std::ifstream testFile(testFilename);
  if (!testFile) {
      std::cerr << "!!! ERROR: Test file not found '" << testFilename << "'" << std::endl;
      std::cerr << "!!! Create it manually before running the test." << std::endl;
  } else {
      testFile.close(); // File exists, we can close it and continue
      
      // 3.2. Run the preprocessor on this file
      try {
          // Use the -P flag to skip extra line info
          std::string result = runPreprocesor(testFilename);
          std::cout << "--- Content of " << testFilename << " after preprocessor ---" << std::endl;
          std::cout << result;
          std::cout << "-----------------------------------------------" << std::endl;
          
          // Store the result in the stream we will use in the interpreter loop
          CommandStream.str(result);

      } catch (const std::runtime_error& e) {
          std::cerr << "!!! Error during preprocessor test: " << e.what() << std::endl;
      }
  }

  // ====================================================================
  // 4. Command interpreter loop
  // ====================================================================
  
  std::cout << "\n--- STARTING INTERPRETER ---" << std::endl;
  std::string CommandName;

  // The loop reads from the stream (filled by the preprocessor)
  // word by word. The first word in a line is the command name.
  while (CommandStream >> CommandName) {

    // Check if the read command exists in our map
    auto CommandIter = CommandMap.find(CommandName);

    if (CommandIter == CommandMap.end()) {
      std::cerr << "!!! ERROR: Unrecognized command: " << CommandName << std::endl;
      // Skip the rest of this line
      std::string restOfLine;
      std::getline(CommandStream, restOfLine);
      continue;
    }

    // Command found.
    // 1. Get the creation function (CreateCmd) from the map
    Fun_CreateCmd pCreateCommand = CommandIter->second;
    // 2. Call it to create the command object
    AbstractInterp4Command *pCommand = pCreateCommand();

    std::cout << "\n> Executing command: " << pCommand->GetCmdName() << std::endl;

    // 3. Call ReadParams to read the rest of the parameters from the line
    if (!pCommand->ReadParams(CommandStream)) {
      std::cerr << "!!! ERROR: Incorrect parameters for command: " << CommandName << std::endl;
      pCommand->PrintSyntax(); // Show the correct syntax
    } else {
      // 4. Display the read parameters (Task 1.5)
      pCommand->PrintCmd();
    }

    // 5. Delete the command object
    delete pCommand;
  }


  // ====================================================================
  // 5. Closing libraries
  // ====================================================================
  
  std::cout << "\n--- CLOSING LIBRARIES ---" << std::endl;
  for (void* pLibraryHandle : LibraryHandles) {
    dlclose(pLibraryHandle);
  }

  return 0;
}