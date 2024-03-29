// Copyright 2021 The Tint Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// builtin-gen parses the <tint>/src/builtins.def file, then scans the
// project directory for '<file>.tmpl' files, to produce '<file>' source code
// files.
package main

import (
	"flag"
	"fmt"
	"io/ioutil"
	"os"
	"path/filepath"
	"strings"

	"dawn.googlesource.com/tint/tools/src/cmd/builtin-gen/gen"
	"dawn.googlesource.com/tint/tools/src/cmd/builtin-gen/parser"
	"dawn.googlesource.com/tint/tools/src/cmd/builtin-gen/resolver"
	"dawn.googlesource.com/tint/tools/src/fileutils"
	"dawn.googlesource.com/tint/tools/src/glob"
)

const defProjectRelPath = "src/builtins.def"

func main() {
	if err := run(); err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
}

func showUsage() {
	fmt.Println(`
builtin-gen generates the builtin table for the Tint compiler

builtin-gen parses the <tint>/src/builtins.def file, then scans the project
directory for '<file>.tmpl' files, to produce '<file>' source code files.

usage:
  builtin-gen

optional flags:`)
	flag.PrintDefaults()
	fmt.Println(``)
	os.Exit(1)
}

func run() error {
	// Load the builtins definition file
	projectRoot := fileutils.ProjectRoot()
	defPath := filepath.Join(projectRoot, defProjectRelPath)

	defSource, err := ioutil.ReadFile(defPath)
	if err != nil {
		return err
	}

	// Parse the definition file to produce an AST
	ast, err := parser.Parse(string(defSource), defProjectRelPath)
	if err != nil {
		return err
	}

	// Resolve the AST to produce the semantic info
	sem, err := resolver.Resolve(ast)
	if err != nil {
		return err
	}

	// Recursively find all the template files in the <tint>/src directory
	files, err := glob.Scan(projectRoot, glob.MustParseConfig(`{
		"paths": [{"include": [
			"src/**.tmpl",
			"test/**.tmpl"
		]}]
	}`))
	if err != nil {
		return err
	}

	// For each template file...
	for _, relTmplPath := range files {
		// Make tmplPath absolute
		tmplPath := filepath.Join(projectRoot, relTmplPath)

		// Read the template file
		tmpl, err := ioutil.ReadFile(tmplPath)
		if err != nil {
			return fmt.Errorf("failed to open '%v': %w", tmplPath, err)
		}

		// Create or update the file at relpath if the file content has changed
		// relpath is a path relative to the template
		writeFile := func(relpath, body string) error {
			// Write the common file header
			sb := strings.Builder{}
			sb.WriteString(fmt.Sprintf(header, filepath.ToSlash(relTmplPath), filepath.ToSlash(defProjectRelPath)))
			sb.WriteString(body)
			content := sb.String()
			abspath := filepath.Join(filepath.Dir(tmplPath), relpath)
			return writeFileIfChanged(abspath, content)
		}

		// Write the content generated using the template and semantic info
		sb := strings.Builder{}
		if err := gen.Generate(sem, string(tmpl), &sb, writeFile); err != nil {
			return fmt.Errorf("while processing '%v': %w", tmplPath, err)
		}

		if body := sb.String(); body != "" {
			_, tmplFileName := filepath.Split(tmplPath)
			outFileName := strings.TrimSuffix(tmplFileName, ".tmpl")
			if err := writeFile(outFileName, body); err != nil {
				return err
			}
		}
	}

	return nil
}

// writes content to path if the file has changed
func writeFileIfChanged(path, content string) error {
	existing, err := ioutil.ReadFile(path)
	if err == nil && string(existing) == content {
		return nil // Not changed
	}
	if err := os.MkdirAll(filepath.Dir(path), 0777); err != nil {
		return fmt.Errorf("failed to create directory for '%v': %w", path, err)
	}
	if err := ioutil.WriteFile(path, []byte(content), 0666); err != nil {
		return fmt.Errorf("failed to write file '%v': %w", path, err)
	}
	return nil
}

const header = `// Copyright 2021 The Tint Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

////////////////////////////////////////////////////////////////////////////////
// File generated by tools/builtin-gen
// using the template:
//   %v
// and the builtin defintion file:
//   %v
//
// Do not modify this file directly
////////////////////////////////////////////////////////////////////////////////

`
