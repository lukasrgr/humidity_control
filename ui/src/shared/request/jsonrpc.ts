export class JsonRpcRequest {
    public constructor(
        public readonly method: string,
        public readonly params: {},
    ) { }
}