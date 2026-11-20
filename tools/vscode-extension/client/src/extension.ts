
import { workspace, ExtensionContext } from 'vscode';

import {
	LanguageClient,
	LanguageClientOptions,
	Executable
} from 'vscode-languageclient/node';

let client: LanguageClient;

export function activate(context: ExtensionContext) {
	const clientOptions: LanguageClientOptions = {
		documentSelector: [{ scheme: 'file', language: 'kuku' }],
		synchronize: {
			fileEvents: workspace.createFileSystemWatcher('**/.clientrc')
		}
	};

	const serverCommand : Executable = {
		command: context.asAbsolutePath("../../build/debug/kuku.exe"),
		args: ["lang-server"]//, "--debug"]
	};

	client = new LanguageClient(
		'kukuLanguageServer',
		'Kuku Language Server',
		serverCommand,
		clientOptions
	);

	client.start();
}

export function deactivate(): Thenable<void> | undefined {
	if (!client) {
		return undefined;
	}
	return client.stop();
}
