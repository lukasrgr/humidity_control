
/**
 * <pre>
 * {
 *   "jsonrpc": "2.0",
 *   "id": UUID,
 *   "method": "addEdgeToUser",
 *   "params": {
 *      "setupPassword": string
 *   }
 * }
 * </pre>
 */
export class AddEdgeToUserRequest {

    static METHOD: string = "addEdgeToUser";

    public constructor(
        public readonly params: {
            setupPassword: string
        }
    ) { }

}