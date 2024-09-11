#!/bin/bash

CONTAINER_NAME="kind_antonelli"

isContainerRunning() {
    docker ps | grep "$CONTAINER_NAME" >/dev/null
}

getContainerId() {
    docker ps -a -q --filter "name=$CONTAINER_NAME"
}

enterContainer() {
    CONTAINER_ID=$(getContainerId)

    if [ -n "$CONTAINER_ID" ]; then
        if isContainerRunning; then
            echo "Connecting to environment..."
            echo "Container ID: $CONTAINER_ID"

            if command -v winpty >/dev/null 2>&1; then
                winpty docker exec -it "$CONTAINER_ID" bash
            else
                docker exec -it "$CONTAINER_ID" bash
            fi
        else
            echo "Container is not running. Please start the container first."
        fi
    else
        echo "No container found with a name containing \"$CONTAINER_NAME\""
    fi
}

# Check the first argument
case "$1" in
    devenv)
        enterContainer
        ;;
    *)
        echo "Usage $0 {devenv}"
        exit 1
        ;;
esac
