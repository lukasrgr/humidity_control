import { Service } from 'src/shared/service';
import { Component } from "@angular/core";

@Component({
    selector: "relayComponent",
    templateUrl: "./relay.html"
})
export class RelayComponent {
    public relayState: RelayState;
    public readonly RelayState = RelayState;

    constructor(
        private service: Service
    ) { }
    ngOnInit() {
        this.service.latestData.subscribe(data => {
            this.relayState = data.relay == 0 ? RelayState.RELAY_CLOSED : RelayState.RELAY_OPEN
        })
    }
}

export enum RelayState {
    RELAY_CLOSED,
    RELAY_OPEN
}

export type GetCurrentRelayStateResponse = {
    relay: number[],
    timestamps: string[]
}